import sys
from PIL import Image

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


if __name__ == "__main__":
    main()
