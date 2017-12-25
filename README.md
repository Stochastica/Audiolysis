# Audiolysis

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

The script `update.py` is used to introduce new source files or new QObject
headers to `CMakeLists.txt`.

All QObject headers must lie in the directory `src/ui/`.

Polygamma's source codes are formatted according to the following astyle
configuration:
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
Polygamma's include guards are formatted according to the `.formatGen` file in
the root directory.

#### Structure

Polygamma usually run in two threads. The GUI/main thread contains all GUI
interactions managed by Qt, and the Kernel thread which contains the function
`void Kernel::start()`. The Kernel must be halted with `void Kernel::halt()`,
otherwise segmentation faults occur upon application exit.

Interthread communication is done with `boost::spsc_queue`s. The Kernel
contains one queue for commands going in and two queues for outputs going
into the GUI.
