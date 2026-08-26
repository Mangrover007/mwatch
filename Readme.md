## Change the base directory

The program uses a base directory for all anime episodes and subs.
Change the base directory by editing the source file `src/main.cpp`:

```cpp
const char* base = <path-to-dir>;
```

For example: `/home/user/anime`

After setting the base directory, run the following commands
to compile the source code:

```bash
mkdir -p build/release/
make DEBUG=0
```

## The anime base directory

This directory should contain a `<name>` directory (for the anime)
and two subdirectories: `episodes` and `subs` (for the episode and
sub files).

For example:

```
/home/user/anime
    -- NoGameNoLife            ! any name is ok
        -- episodes            ! case sensitive
        -- subs                ! case sensitive
```

To run an anime from `/home/user/anime` directory, run the
following command:

```bash
./build/release/mwatch.out --anime=<anime-name> --ep=<episode-number>
```

For example, if the directory structure is as described above,
run:

```
./build/release/mwatch.out --anime="NoGameNoLife" --ep=1
```

## Global launch

To launch the anime from anywhere, you can define an alias in
your shell start up script. For bash:

```bash
alias mwatch=<full-path-to-executable>

# for example:
# alias mwatch="/home/user/<proj-dir>/scripting/mwatch/build/release/mwatch.out"
```

Additionally, you can also build it with debug logs enabled by
setting `DEBUG=1` during `make DEBUG=` near the very top of this
Readme.

Have fun :D

P.S. I was tired of writing the whole command and the full file names
of the episodes. I have JP subs for the anime I watch and so I need
to subsitute that sub file instead of the normal EN subs that anime
usually comes with. That was why I created this small project.

