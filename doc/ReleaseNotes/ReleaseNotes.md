# OpenStudio 2.0 Prerelease

This is an alpha quality build of OpenStudio 2.0. This is an aggressive overhaul of OpenStudio to make the SDK smaller and more accessible. The first component and the focal point of the overhaul is a command line interface that is capable of executing OpenStudio workflows. Principally this means that it is capable of running OpenStudio Measures. The command line is fully self contained, requiring no outside dependencies beyond the system runtime libraries. Ruby and standard librarys are statically linked and archived into the executable.

Additional components will be added as optional components in the installer as they are brought back online. Namely the OpenStudio Application and SketchUp Plugin. At this time the command line interface is the only executable in this package.

## Example Usage

This is an example workflow included in this package as ```compact_osw``` under the Examples directory. This example contains everything to run a simple OpenStudio workflow from seed model, to applying measures, to running EnergyPlus. 

```
cd path/to/Examples/compact_osw
./path/to/openstudio.exe run -w compact.osw
```

The OpenStudio command line needs to access EnergyPlus. It will do this by first looking for the environment variable ENERGYPLUS_EXE_PATH, and then by looking in the standard EnergyPlus install location for the system.

## Note about versioning

```
openstudio.exe openstudio_version
```

This command will report out the version of the OpenStudio command line interface. At this time, even though this is a 2.0 preview, the version will be reported as 1.x.y corresponding to the version of the OpenStudio model for which it is compatiable.

## Ruby Bindings

The OpenStudio Ruby Bindings are now contained in a single shared library named openstudio.so (.bundle on Mac), located in the installations bin directory. Ruby 2.0.0 is required.

## Known Issues

Too many to list. This is a work in progress.

* Missing Ruby libraries. Most of the Ruby standard library is available from command line interface and therefore accessible from OpenStudio Measures. There are a few libraries that are still missing.
* Incomplete. There is no Standards Gem, or Prototype buildings included in the package. Those things are coming.

## Updates

