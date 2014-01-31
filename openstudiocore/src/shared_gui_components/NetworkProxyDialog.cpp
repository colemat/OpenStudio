#include "NetworkProxyDialog.hpp"
#include "../utilities/core/String.hpp"
#include "../utilities/core/Application.hpp"

#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QInputDialog>
#include <QNetworkReply>
#include <QEventLoop>

#include <utility>

#include "../utilities/time/Time.hpp"

#include <iostream>

namespace openstudio
{
  NetworkProxyDialog::NetworkProxyDialog(QSettings &t_settings, QWidget *t_parent = 0)
    : QDialog(t_parent), 
      m_settings(t_settings)
  {
    QGridLayout *layout = new QGridLayout(this);

    // NoProxy, DefaultProxy, Socks5Proxy, HttpProxy, HttpCachingProxy, FtpCachingProxy
    m_proxyType = new QComboBox();
    m_proxyType->addItem("No Proxy", QNetworkProxy::NoProxy);
    // Allow http only for now since that's known to be supported by ruby / aws
    // m_proxyType->addItem("Socks5 Proxy", QNetworkProxy::Socks5Proxy);
    m_proxyType->addItem("Http Proxy", QNetworkProxy::HttpProxy);

    connect(m_proxyType, SIGNAL(currentIndexChanged(int)), this, SLOT(proxyTypeChanged(int)));

    m_hostName = new QLineEdit(this);
    m_port = new QLineEdit(this);
    m_port->setValidator(new QIntValidator(0, 65535));

    m_user = new QLineEdit(this);


    layout->addWidget(new QLabel("Proxy Type"), 0, 0);
    layout->addWidget(m_proxyType, 0, 1);
    layout->addWidget(new QLabel("Host Name"), 1, 0);
    layout->addWidget(m_hostName, 1, 1);
    layout->addWidget(new QLabel("Port"), 2, 0);
    layout->addWidget(m_port, 2, 1);
    layout->addWidget(new QLabel("User Name"), 3, 0);
    layout->addWidget(m_user, 3, 1);
    
    QHBoxLayout *buttonBox = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Save");
    QPushButton *cancelButton = new QPushButton("Cancel");
    QPushButton *testButton = new QPushButton("Test");
   
    buttonBox->addWidget(saveButton);
    buttonBox->addWidget(cancelButton);
    buttonBox->addWidget(testButton);

    layout->addLayout(buttonBox, 4,0,1,2);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    connect(testButton, SIGNAL(clicked()), this, SLOT(testClicked()));

    QNetworkProxy proxy(createProxy(t_settings));

    int type = m_proxyType->findData(proxy.type());
    QString user = proxy.user();
    QString hostname = proxy.hostName();
    int port = proxy.port();

    m_proxyType->setCurrentIndex(type>-1?type:0);
    m_user->setText(user);
    m_hostName->setText(hostname);
    m_port->setText(QString::number(port));
    proxyTypeChanged(m_proxyType->currentIndex());
  }

  void NetworkProxyDialog::proxyTypeChanged(int index)
  {
    if (QNetworkProxy::NoProxy == m_proxyType->itemData(index).toInt())
    {
      m_hostName->setEnabled(false);
      m_port->setEnabled(false);
      m_user->setEnabled(false);
    } else {
      m_hostName->setEnabled(true);
      m_port->setEnabled(true);
      m_user->setEnabled(true);
    }
  }

  void NetworkProxyDialog::saveClicked()
  {
    accept();
  }

  void NetworkProxyDialog::cancelClicked()
  {
    reject();
  }

  void NetworkProxyDialog::testClicked()
  {
    QSettings set;
    setSettings(set);

    QNetworkProxy proxy(createProxy(set));
    if (testProxy(proxy))
    {
      QMessageBox::information(this, "Test Succeeded", "Proxy configuration test passed.");
    } else {
      QMessageBox::critical(this, "Test Failed", "Proxy configuration test failed.");
    }
  }

  std::pair<QNetworkReply::NetworkError, QString> NetworkProxyDialog::testProxyConnection(const QNetworkProxy &t_proxy)
  {
    QNetworkAccessManager nam;
    nam.setProxy(t_proxy);
    QNetworkReply *head = nam.head(QNetworkRequest(QUrl("https://bcl.nrel.gov/")));

    if (!head) return std::make_pair(QNetworkReply::UnknownNetworkError, QString("Unknown error creating connection to proxy."));


    boost::posix_time::ptime start = boost::posix_time::microsec_clock::universal_time();

    while ( !head->isFinished()
            && (boost::posix_time::microsec_clock::universal_time() - start).total_milliseconds() < 10000)
    {
      Application::instance().processEvents();
    }

    head->deleteLater();

    if (!head->isFinished()) 
    {
      head->abort();
      return std::make_pair(QNetworkReply::TimeoutError, QString("Timed out while attempting to verify proxy connection"));
    }

    LOG(Debug, " errorString from proxy test " << toString(head->errorString()) << " " << head->error());

    return std::make_pair(head->error(), head->errorString());
  }

  bool NetworkProxyDialog::testProxy(QNetworkProxy &t_proxy, QWidget *t_parent)
  {
    if (t_proxy.type() == QNetworkProxy::NoProxy) return true;

    t_parent->setEnabled(false);
    
    bool retval = false;
    bool cont = true;
    while (cont)
    {
      std::pair<QNetworkReply::NetworkError, QString> err = testProxyConnection(t_proxy);
      switch (err.first)
      {
      case QNetworkReply::ProxyAuthenticationRequiredError:
        {
          bool ok;
          QString password = QInputDialog::getText(t_parent, "Proxy Password", "Proxy authentication failed, please enter network proxy password for user '" + t_proxy.user() + "'.", QLineEdit::Password, "", &ok);

          if (ok)
          {
            t_proxy.setPassword(password);
          } else {
            t_parent->setEnabled(true);
            retval = false;
            cont = false;
          }
        }
        break;

      case QNetworkReply::ProxyConnectionClosedError:
      case QNetworkReply::ProxyConnectionRefusedError:
      case QNetworkReply::ProxyNotFoundError:
      case QNetworkReply::ProxyTimeoutError:
      case QNetworkReply::UnknownProxyError:
        {
          QMessageBox::critical(t_parent, "Error Communicating with Proxy", "Proxy network error: " + err.second);
          t_parent->setEnabled(true);
          retval = false;
          cont = false;
          break;
        }

      case QNetworkReply::NoError:
        {
          t_parent->setEnabled(true);
          retval = true;
          cont = false;
          break;
        }

      default:
        {
          QMessageBox::critical(t_parent, "Unknown Error While Checking Proxy", "Error: " + err.second);
          t_parent->setEnabled(true);
          retval = false;
          cont = false;
        }

      }
    }

    return retval;
  }


  bool NetworkProxyDialog::testProxy(QNetworkProxy &t_proxy)
  {
    return testProxy(t_proxy, this);
  }

  void NetworkProxyDialog::setSettings(QSettings &t_settings) const
  {
    t_settings.setValue("networkproxy_type", m_proxyType->itemData(m_proxyType->currentIndex()));
    t_settings.setValue("networkproxy_hostname", m_hostName->text());
    t_settings.setValue("networkproxy_port", m_port->text());
    t_settings.setValue("networkproxy_user", m_user->text());
  }

  QNetworkProxy NetworkProxyDialog::createProxy()
  {
    setSettings(m_settings);
    return createProxy(m_settings);
  }

  QNetworkProxy NetworkProxyDialog::createProxy(const QSettings &t_settings)
  {
    QNetworkProxy::ProxyType type = static_cast<QNetworkProxy::ProxyType>(t_settings.value("networkproxy_type", QNetworkProxy::NoProxy).toInt());
    QString hostname = t_settings.value("networkproxy_hostname").toString();
    int port = t_settings.value("networkproxy_port").toInt();
    QString user = t_settings.value("networkproxy_user").toString();
    return QNetworkProxy(type, hostname, port, user, "");
  }

}


