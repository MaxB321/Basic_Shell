THIS IS A SIMPLE WINDOWS TERMINAL!

Featured Commands:
  1. exit
  2. echo
  3. pwd
  4. cd
    - special chars:
      - . (keep current directory)
      - .. (go to parent directory)
      - / (go to root directory)
      - ./ (use relative pathing)
        - relative pathing is default if you do not specify path (ex: cd dir_name | cd ./dir_name)
  5. ls
  6. clear
  7. touch
  8. mkdir
  9. rm  
  10. rm -r
  11. cat
  12. grep
    - Flags: -i, -r (case insensitive and recursive respectively)
    - Can use these one or both flags 
    - ex: grep -i -r text dir_name 
  13. cp
  14. mv


**BUILD GUIDE**

To build, simply run the build script with the Debug/Release Argument. If no argument is specified it will default to Debug Build.
Ex: .\build.bat Debug

The clean script works in the same way. If no argument is specified it will clean both debug and release builds.