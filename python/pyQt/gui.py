import sys
import socket
from PyQt5.QtWidgets import QApplication, QPushButton, QWidget, QFileDialog, QLineEdit, QLayout


def mergeFile(fileNames):
    file1 = open(fileNames[0], "w+")
    file2 = open(fileNames[1], "w+")
    content = file1.read(140000)
    tmp = file2.read()
    print(content)

    pass

class mainWidget():
    def __init__(self):  # real signature unknown; restored from __doc__
        self.win = QWidget()
        # self.win.setFixedSize()
        self.openBtn = QPushButton(self.win)
        self.openBtn.setText("打开文件")
        self.openBtn.clicked.connect(self.openDir)
        # self.layout = QLayout()
        pass

    def showWin(self):
        self.win.show()

        pass

    def openDir(self):
        fileNames, fileType = QFileDialog.getOpenFileNames()
        mergeFile(fileNames)
        pass



def main():
    app = QApplication(sys.argv)
    win = mainWidget()
    win.showWin()

    sys.exit(app.exec())

if __name__ == '__main__':
    main()