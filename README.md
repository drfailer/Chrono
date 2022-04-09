# chrono

Very basic tui-chronometer.

## Usage

### Basic

The following will start a chronometer from `00:00` to `99:59`.

```bash
chrono
```

Result:

```
+-------+
| mm:ss |
+-------+
```

Hit `C-c` to stop the program (I don't use ncurses to capture
keybinding, I kept it very simple).

### Timer

It can be used as a timer with a given time:

```bash
# wait 1 min and 30 seconds
chrono 1:30
```