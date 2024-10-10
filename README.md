AeroCalc is a command line tool that I built to help with my rc plane dimension calculations.
It was inspired by Chuck Cunningham's RC Design Made Easy guide.
The guide can be found at [Chuck Cunningham's RC Design Made Easy](https://www.rcuniverse.com/forum/scratch-building-aircraft-design-3d-cad-174/11560594-cunninghams-rcm-design-information.html)  
If you clone the project and add other features please submit a pull request. :)

Usage: AeroCalc [option]  
AeroCalc [Wingspan] [FuselageLengthModifier] [WingRootChordModifier] [WingTipChordModifier] [HStabAreaModifier] [vStabAreaModifier] [Weight]

Options:  
-h, --help			Print command line options"

Running program without arguments uses default values for airplane settings

Default values:  
Wingspan = 48 inches  
FuselageLength = FuseLenModifier(0...1) is 75% of wingspan  
WingRootChord = WingRootChordModifier(0...1) is 16.67% of wingspan or 1/6 of wingspan  
WingTipChord = WingTipChordModifier(0...1) is 100% of wingRootChord  
HorizontalStabArea = HStabAreaModifier(0...1) is 22.5% of winspan area  
VerticalStabArea = VStabAreaModifier(0...1) is 11.25% of winspan area  
Weight = 1000 grams (Estimate used for approximating wing load)  

After building the project using Visual Studio, you can add the path of the executable to the environmental variables and run it directly from the command prompt.  
You can also 'cd' into the folder containing the executable using the command prompt and run it from there