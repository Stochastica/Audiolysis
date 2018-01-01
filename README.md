# Audiolysis

![Audiolysis](doc/logo.png)

An audio visualisation and editing tool.

## Usage

Coming soon...

## Building

It is best to do an out of source build at `build/` directory. Create a
subdirectory `build` and run
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

## Developing

#### Conventions and scripts

All QObject headers must lie in the directory `src/ui/`.

The source code is formatted according to the following astyle configuration:
```
--style=allman
--align-pointer=type	
--close-templates
--convert-tabs
--indent-preproc-block
--indent-preproc-define
--indent=tab=2
--pad-header
--unpad-paren
```
