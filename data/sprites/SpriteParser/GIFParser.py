from PIL import Image, ImageSequence
import numpy as np
import os

#   Format:
#
#   number of sequences
#   {
#       sequence name
#       number of frames in sequence
#       width of each frame (pixels)
#       height of each frame (pixels)
#       {
#           (total number of colors in line) (color index) (number of repeated color) ...
#       }
#       ...
#   }

#   CONFIG
backgroundColor = 0x00FF00
characterName = "kirby"
imageDirectory = "/gif-" + characterName + "/"

# Output file
output = open(characterName + ".txt", "w")

indexed_rgb = []

numFiles = len(os.listdir(os.getcwd() + "/gif-kirby/"))
output.write(str(numFiles))
for filename in os.listdir(os.getcwd() + "/gif-kirby/"):
    if filename.endswith(".gif") or filename.endswith(".png"):
        img = Image.open("./gif-kirby/" + filename)
        frames = np.array([np.array(frame.copy().convert('RGB').getdata(), dtype=np.uint8)
                          .reshape(frame.size[1], frame.size[0], 3) for frame in ImageSequence.Iterator(img)])
        compressed_rgb = []

        frame_width = 0
        frame_height = 0

        # Convert 8-bit color to 6-bit color and store in index array
        for frame in frames:
            compressed_frame = []
            frame_height = len(frame)
            for row in frame:
                frame_width = len(row);
                compressed_row = []
                prev_color = 0
                line_len = 1
                for i, pixel in enumerate(row):
                    red = int(pixel[0])
                    green = int(pixel[1])
                    blue = int(pixel[2])
                    rgb_int = red << 16 | green << 8 | blue
                    if rgb_int == backgroundColor:
                        rgb_int = -1
                    if rgb_int == prev_color:
                        line_len += 1
                        if i == len(row)-1:
                            compressed_row.append([indexed_rgb.index(prev_color), line_len])
                    else:
                        if not indexed_rgb.__contains__(rgb_int):
                            indexed_rgb.append(rgb_int)
                        if i != 0:
                            compressed_row.append([indexed_rgb.index(prev_color), line_len])
                        prev_color = rgb_int
                        line_len = 1
                compressed_frame.append(compressed_row)
            compressed_rgb.append(compressed_frame)

        # Write to file
        output.write("\n")
        output.write(filename.split(".")[0] + "\n")
        output.write(str(len(frames)) + "\n")
        output.write(str(frame_width) + "\n")
        output.write(str(frame_height))
        for frame in compressed_rgb:
            for row in frame:
                output.write("\n")
                output.write(f"{len(row)}")
                for line in row:
                    output.write(f" {line[0]} {line[1]}")
output.write(f"Colors: \n {indexed_rgb}\n")



