CityHook
--------

Allows you to monitor all CityHash calls made by MGS, each time the CityHash functions are called the value being hashed will be logged to [MGS-dir]\logger.log

Two versions are included:
- CityHook_paths.dll: will only log values that look like paths (contain a '/' or '\\' character, or end in .lua/.json/.fpk(d)/.ftexs)
- CityHook_all.dll: will log ALL CityHash calls, might be useful for finding matches for other things besides QAR archives (will probably slow your game down a bit though!)

(both DLLs are built with Visual Studio 2017, make sure you have "Visual C++ 2017 redistributable" installed to use them!)

To install just rename the DLL of your choice to dinput8.dll and copy it next to mgv.exe.

Source code is included, right now it's only setup for Survive 1.02 but it should be easy to port to other Fox Engine titles.  
(tip: try searching the exe for the constants used by CityHash, eg. 0x9ae16a3b2f90404f, you might need to reverse the constant to be little-endian first though)

If you have any problems please feel free to post on the issue tracker!