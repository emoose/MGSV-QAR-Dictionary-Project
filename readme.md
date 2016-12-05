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
These stats are based on TPP PC v1.10 and the latest commit to this repo:

# Archive Stats

|QAR filename|Files|Named|Unnamed|Average|Notes|
|---|---|---|---|---|---|
|gzs\data_01.g0s|15329|14059|1270|91.72%||
|gzs\data_02.g0s|893|863|30|96.64%||
|mgo\chunk0.dat|3814|3263|551|85.55%||
|mgo\texture0.dat|19975|11103|8872|55.58%||
|pt\texture.qar|4862|4862|0|100%||
|tpp\chunk0.dat|2885|2870|15|99.48%||
|tpp\chunk1.dat|4375|4367|8|99.82%||
|tpp\chunk2.dat|14115|14115|0|100%|Complete|
|tpp\chunk3.dat|1948|1944|4|99.79%||
|tpp\chunk4.dat|13722|13722|0|100%|Complete|
|tpp\data1.dat|623|621|2|99.68%|Every file named except fb73c9483333.subp and 3989933189c50.subp|
|tpp\texture0.dat|33359|21713|11646|65.09%||
|tpp\texture1.dat|8804|8614|190|97.84%||
|tpp\texture2.dat|21059|14753|6306|70.06%||
|tpp\texture3.dat|14796|5804|8992|39.23%||
|tpp\texture4.dat|16557|10265|6292|62.00%||
|tpp\0\00.dat|756|732|24|96.83%|chunk patches|
|tpp\0\01.dat|745|231|514|31.01%|texture patches|
|tpp\1\00.dat|712|711|1|99.86%|Every file named except 32aaad214906d.dat. Seems to be similar to foxpatch.dat|
|tpp\1\01.dat|5585|2236|3349|40.04%|texture patches|
|Total:|184914|136848|48066|74.00%|All files|
|Total:|43843|43208|635|98.55%|Without texture files|

# Filetype Stats

|File type|File count|Named count|Unnamed count|Completion %|Notes|
|---|---|---|---|---|---|
|.wem|305|305|0|100.00%|tp_m_10160_03 (Ep. 51 convo) and tp_m_10260_02 (convo about quiet) are unused ingame|
|.rdf|6|6|0|100.00%||
|.sani|4|4|0|100.00%||
|.json|39|39|0|100.00%||
|.fsop|8|8|0|100.00%||
|.fstb|1|1|0|100.00%||
|.ffnt|13|13|0|100.00%||
|.fmtt|4|4|0|100.00%||
|.fox|3|3|0|100.00%||
|.bnk|2|2|0|100.00%||
|.subp|489|487|2|99.59%||
|.fsm|321|319|2|99.38%||
|.fpk|18672|18451|221|98.82%||
|.fpkd|18607|18386|221|98.81%||
|.sbp|348|342|6|98.28%||
|.pftxs|4401|4281|120|97.27%||
|.lua|599|554|45|92.49%||
|.dat|4|3|1|75.00%||
|.ftex|30442|20323|10119|66.76%||
|.ftexs|105767|68455|37312|64.72%||
|.gani|1|0|1|0.00%||

Some console-only files have also been named (along with MGO-related files included in console data), but console-only files aren't included in the stats above.

## Additions
As said above additions are welcomed and appreciated, simply make a pull request with your changes and it'll be merged in and cleaned up afterward (making sure you keep credit in the commit log)

If you're unable to make a pull request you could also make an issue in the issue tracker with the changes you want, they'll be added in and a credit to you will be added below.

## Observations
A few things I've noticed while making this dictionary:

- Some fpk/fpkd files have the same filenames as .fox2 files mentioned inside .fpkd archives, or filenames that are very close to the .fox2 filename.
- Only certain filenames used by Ground Zeroes include the extension of the file, in TPP all filename extensions are hashed seperately, so we don't need to include them.
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
