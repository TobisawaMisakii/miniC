#!/usr/bin/env python3
import os
import zipfile
from pathlib import Path

def create_zip_with_exclusions(source_dir, output_zip, exclusions=None):
    """
    将指定文件夹打包为ZIP，并排除指定的文件和文件夹

    参数:
        source_dir (str): 要打包的源文件夹路径
        output_zip (str): 输出的ZIP文件路径
        exclusions (list): 要排除的文件/文件夹列表（相对路径）
    """
    # 如果zip文件已存在，则删除它
    if os.path.exists(output_zip):
        os.remove(output_zip)

    if exclusions is None:
        exclusions = []

    source_path = Path(source_dir).resolve()
    output_path = Path(output_zip).resolve()

    print(f"正在打包文件夹: {source_path}")
    print(f"排除列表: {exclusions}")

    with zipfile.ZipFile(output_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, dirs, files in os.walk(source_path):
            # 移除排除的文件(夹)，防止os.walk遍历它们
            dirs[:] = [d for d in dirs if str(Path(root, d).relative_to(source_path)) not in exclusions]

            for file in files:
                file_path = Path(root, file)
                rel_path = file_path.relative_to(source_path)

                if str(rel_path) not in exclusions:
                    print(f"添加: {rel_path}")
                    zipf.write(file_path, rel_path)
                else:
                    print(f"排除: {rel_path}")
    print(f"\nZIP文件已创建: {output_path}")


if __name__ == '__main__':
    source_dir = '../miniC'
    output_zip = '../miniC_oj.zip'
    exclude = [
        'build',
        '.vscode',
        'doc',
        '.git',
        '*.md',
        'LICENSE',
        '*.assets',
        'IRCompiler',
        'tools',
        'thirdparty',
        '.idea',
        'tests',
        '2023function-tests',
        '2025function-tests',
        '2025performance-tests',
        'oj_upload.py',
        '*.sh',
        'Doxygen.config',
        '*.png'
    ]
    create_zip_with_exclusions(source_dir, output_zip, exclude)