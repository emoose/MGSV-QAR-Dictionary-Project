# MGSV QAR Dictionary Project

The QAR dictionary project is a project to name every file used in MGSV Ground Zeroes and The Phantom Pain.

Unfortunately for modders MGSV is hard to mod mostly because we don't know the filenames of everything used in the game, as the games archives use CityHash hashes to identify files.  
This is fine for a game which knows what data it wants to use, but makes it hard for modders to find/categorize data used by the game without resorting to reverse engineering/bruteforcing, making a modders job a lot harder.

Eg. if the game wants the file "/Fox/Scripts/Gr/gr_init.lua" it would just hash the string "/Fox/Scripts/Gr/gr_init", then search inside its data archives for the hash of it (eg 0x3228caff179b0) to get the data for that file.  
But if modders don't know the file is called "/Fox/Scripts/Gr/gr_init.lua" then it'll be a tough job for them to find it.

That's why the MGSV QAR Dictionary Project is a project to name every file in MGSV, so that modders have a reference of known filenames to use, and a place to help out other modders by adding any others they find.

The project contains a dictionary.txt file for use with QAR file extractors such as MGSV QAR Tool and GzsTool, it also contains a complete list of hashes used by the game for reference.

Pull requests are welcomed if anyone has any additions, maybe with your help one day we'll have a complete dictionary.  
Though note this dictionary has been optimized to only include filenames actually used inside QAR files, which is why it's so small compared to other dictionaries.  
The hash reference lists can be used to make sure any additions are actually used by the game, it's not required for you to check your additions as we can do that for you, but if you can check them yourself first it'd be appreciated.

## Sources
Filenames have been sourced from a few different places:

- dictionaries included with MGSV QAR Tool and GzsTool, and filename lists posted on various websites.
- scraping from LUA and binary files.
- bruteforcing (trying out different combinations of known paths combined with filenames inside fpk archives)

## Stats
These stats are based on TPP PC v1.006 and the initial commit to this repo:

|QAR filename|File count|Named count|Unnamed count|Completion %|Notes|
|---|---|---|---|---|---|
|data1.dat|735|623|112|84.76%|Every file named except .subp files|
|chunk0.dat|2885|2286|599|79.23%||
|chunk1.dat|4375|4210|165|96.22%||
|chunk2.dat|14115|5262|8853|37.27%||
|chunk3.dat|1948|907|1041|46.56%||
|chunk4.dat|13722|3756|9966|27.37%||
|texture0.dat|33363|8478|24885|25.41%||
|texture1.dat|8804|0|8804|0.00%||
|texture2.dat|21059|1931|19128|9.16%||
|texture3.dat|14796|946|13850|6.39%||
|texture4.dat|16557|1502|15055|9.07%||
|Total:|132359|29901|102458|22.59%|45.11% completion w/o textures|

|File type|File count|Named count|Unnamed count|Completion %|Notes|
|---|---|---|---|---|---|
|.lua files|120|120|0|100%||
|.wem files|255|255|0|100%|tp_m_10160_03 (Ep. 51 convo) and tp_m_10260_02 (convo about quiet) are unused ingame|
|.sbp files|212|201|11|94.81%||
|.fsm files|235|225|10|95.74%||
|.fpk/fpkd files|16637|6655|9982|40.00%||
|.pftxs files|3068|2429|639|79.19%||

Some console-only files have also been named (along with MGO-related files included in console data), but console-only files aren't included in the stats above.

## Additions
As said above additions are welcomed and appreciated, simply make a pull request with your changes and it'll be merged in and cleaned up afterward (making sure you keep credit in the commit log)

If you're unable to make a pull request you could also make an issue in the issue tracker with the changes you want, they'll be added in and a credit to you will be added below.

## Observations
A few things I've noticed while making this dictionary:

- Some fpk/fpkd files have the same filenames as .fox2 files mentioned inside .fpkd archives, or filenames that are very close to the .fox2 filename.
- File extensions aren't used for any hashes - unsure why other dictionaries have entries that have file extensions.
- Some files don't seem to have any references to them, maybe they're referenced by their actual filename hash?
- Files are stored alphabetically inside QAR files, so eg. if you have the following in the QAR entry list:  
2a6874cbc1dde.fpk (/Assets/eg/test1)  
42f099a274ef.fpk  
3107249b91b84.fpk (/Assets/eg/test3)  
There's a good chance the 42f099a274ef.fpk above would be /Assets/eg/test2.fpk

## Thanks
Thanks to Sergeanur for the QAR Tool and dictionary, and major thanks to Atvaark for opensourcing GzsTool, helped a lot while working on tools to help with this dictionary.

Also thanks to cra0kalo, Shigu and others in the XeNTaX thread for their filename lists and tools.

## License
I'm not really sure how I could license this, since many places have been sourced for this list and I'm not sure of the license status of them all...

So we'll just say that you're free to use this dictionary however you like, include it with your tools etc as you want :)  
If you do include it with something a mention of the project would be nice though, since it may help forward more additions to us, but it's not a requirement.