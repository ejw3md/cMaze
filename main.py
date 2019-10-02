import sys
import os
import subprocess
from PIL import Image

def get_filename(name):
    if not os.path.isdir('solved'):
        os.mkdir('solved')
    idx_slash = name.rfind('/')
    idx_dot = name.find('.')
    return "solved" + name[idx_slash:idx_dot] + "_solved" + name[idx_dot:]

def draw_path(im, cData, in_name):
    im = im.convert('RGB')
    impixels = im.load()

    f = open(cData, 'r')
    for line in f:
        s = [int(x) for x in line.split()]
        coord = tuple(s[::-1])
        impixels[coord] = (255, 0, 0)
    im.save(get_filename(in_name))

def write(im):
    f = open('temp.txt', 'w')
    cols = im.size[0]
    rows = im.size[1]
    seq_data = list(im.getdata(0))
    idx = 0
    f.write("%d %d\n" %(rows, cols))
    for i in range(0, rows):
        for j in range(cols):
            f.write(str(seq_data[idx]))
            idx += 1
        f.write('\n')
    f.close()
def main():
    if len(sys.argv) != 2:
        print("Command line format is python3 main.py <name of file>")
        exit()
    try:
        im = Image.open(sys.argv[1])
    except IOError:
        print("Could not open file %s" % sys.argv[1])
        exit()
    write(im)
    subprocess.call(["make"])
    subprocess.call(["./a.out", "temp.txt"], stdin = sys.stdin)

    draw_path(im, "temp2.txt", sys.argv[1])
    os.remove("temp2.txt")
    os.remove("temp.txt")



if __name__ == "__main__":
    main()
