# InjectorTemplate
Simple quickstarter template for Injector. Useful for patching and modding games and other softwares.  

This project uses Injector, a high level and modern injector library, useful for game/software patching, hooking etc.  
https://github.com/thelink2012/injector  

And IniReader, a simple ini parser:  
https://github.com/ThirteenAG/IniReader  

This project was initially worked by me for faster creation of patches and mods for games not originally supported for coding mods.  
For this reason, it originally compiles into .asi, which is simply a renamed DLL.
Use Ultimate ASI Loader for .asi file injection:
https://github.com/ThirteenAG/Ultimate-ASI-Loader  

If your case is .dll for some software or games that Ultimate ASI Loader does not support (which is very rare), change the build file extension and use some appropriate DLL injector.  

This is a simple quickstart solution, not an advanced tool. If you intend to use it to develop game patches and mods, first check if such a game already has any sdk for it.  

Use example:  
https://github.com/JuniorDjjr/RCT3-MixSets
