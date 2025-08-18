import argparse
from PIL import Image

def png_to_ico(png_file, ico_file, size):
    # 打开PNG文件
    img = Image.open(png_file)
    
    # 调整图像大小
    try:
        img = img.resize((size, size), Image.Resampling.LANCZOS)
    except:
        img = img.resize((size, size), Image.ANTIALIAS)
    
    # 将PNG图像转换为ICO格式并保存
    img.save(ico_file, format='ICO')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Convert PNG to ICO")
    parser.add_argument('-i', '--input', required=True, help="Input PNG file path")
    parser.add_argument('-o', '--output', required=True, help="Output ICO file path")
    parser.add_argument('-c', '--size', type=int, default=32, help="Icon size (e.g., 16, 32, 48, etc.)")
    
    args = parser.parse_args()
    
    png_to_ico(args.input, args.output, args.size)
    print("转换完成！")
