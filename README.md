# Silent Hill 2 Save Decryptor

Just works for Silent Hill 2, i didn't make any research on other Silent Hill game's save system so i'm not sure is this program compatible with other.

Usage is simple you can simply put your save file on to exe or you can use like this

SaveDecryptor.exe ```[Options]``` ```[FileName].dat```

Options are:
```
-d/--decrypt - For decrypting save file
-e/--encrypt - For encrypting save file  
```
After you edit save file, make sure .hashkey file in the same folder with decrypted file. After encrypted file, remove file extension until it seems like this [FileName].dat 

I used premake to generate solution files so you can use any other IDE platform. Also i didn't use any windows specific libraries so i didn't tested but it should support other OS's. 

## Editing Save Files

You can use a memory editor to edit datas. There is a lot of tutorials on youtube you can watch them to use or you can wait a GUI save editor.

### Example Usage on HxD:

- After you decrypted save file, put your decrypted save file to HxD.
- Lets assume your ammo in game is 147, press CTRL + F
- Click to the integer number and write your ammo to there and press "Search All" button then start editing

Or you can watch this video to learn hex editing: https://www.youtube.com/watch?v=SYlgoNQpRWI

## WARNING
Make sure you backup save data, i didn't make any checksum correction so it may harm your save data.

## TODO

* There is a bug on encrypt functions i didn't recognize because of that i had to call decryption and encryption functions twice while encrypting.
* I have to make more simple Save-Decrypt library for who wants to use this library.
* After i solve that 2 problem, i will work on GUI Save Editor.
