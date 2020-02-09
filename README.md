## About

This is a simple note taking command-line tool. 

## Usage:

Take simple day-to-day notes:

```
$ note "get some bagels for tomorrow"
$ note "don't forget the lemons"
```

The above appends to `notes.txt` in your `$HOME` directory:

```
$ cat ~/notes.txt
2020-02-08--15:07:47 @@ get some bagels for tomorrow
2020-02-08--15:07:53 @@ don't forget the lemons
```

## Installation:

Run the following from a cloned repo on Linux or MacOS (requires make and gcc-c++):

```
make install
```
