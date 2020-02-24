# IVEx - JJ Current/Voltage Characteristics Extraction Tool
### Introduction
IV Ex(tractor) is a command line tool created to extract the current/voltage characteristics of a Josephson junction. With the capability to generate a *.model* SPICE card it utilizes the [JoSIM](https://github.com/JoeyDelp/JoSIM.git) library to seamlessly simulate and generate the IV curve data.

### Usage
```
ivex [-d data.iv] ".model" | file.model
```
This command takes a *.model* card either by string or through a file containing the model. When IV data
is specified with the *-d* switch, the string is ignored if specified and a *.model* card is produced to match the IV data. If a file name is specified along with the IV data, the file is opened (created if it does not exist) and the generated *.model* card is appended to the opened file.

The syntax required/produced for the JJ model follows the syntax guideline specified here: [JJ Syntax](https://joeydelp.github.io/JoSIM/syntax/#josephson-junction-jj)

---

### Changelog:
### Version 0.1:
- Initial commit
