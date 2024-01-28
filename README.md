
# 🚀 Easy DLL GUI

Just a little tired that's all? I mean tired of all the GUI libraries where you have to write a bunch of OOP code to display just one button?

## 💻 If you need simple GUI library for your DLL in external window format - this repo for you.

Powered by OpenGL 2 && ImGui

## Test it in Python:

```python
import ctypes
from ctypes import cdll

dll = cdll.LoadLibrary('dllmenu.dll')
dll.startGui() // prints "1" and shows GUI

str = '{"time":"07:08","method":"GET","status":"200","url":"https://example.com"}'
bstr = str.encode('utf-8')
dll.addData.argtypes = [ctypes.c_char_p, ctypes.c_int]
dll.addData(bstr, len(str)) // adds row to GUI example

dll.clearData() // clears all rows from GUI example

dll.stopGui() // prints "1" and closes GUI

```

### Works everywhere: if that UWP app

![1](https://i.ibb.co/WxxyywC/image.png)

### ... or Browser

![2](https://i.ibb.co/whBn5nF/image.png)

### ... or even Explorer

![3](https://i.ibb.co/hsZgnTx/image.png)