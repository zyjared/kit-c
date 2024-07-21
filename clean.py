import os
import re


def delete_files_by_regex(folder_path, regex_list, ignore=[]):
    for filename in os.listdir(folder_path):

        if filename in ignore:
            continue

        path = os.path.join(folder_path, filename)

        if os.path.isdir(path):
            delete_files_by_regex((path), regex_list, ignore)

        relative_path = os.path.relpath(path, '.')
        for regex_pattern in regex_list:
            if re.search(regex_pattern, filename):
                try:
                    os.remove(path)
                    print(f"Deleted: {relative_path}")
                except OSError as e:
                    print(f"Error deleting {relative_path}: {e}")


if __name__ == "__main__":

    if len(os.sys.argv) > 1:
        folder = os.sys.argv[1]
    else:
        folder = '.'

    ignore = ['.git', 'build', 'dist', '.vscode', 'node_modules', 'docs']

    regex_list = [
        r'.*\.(exe|EXE|dat|DAT)$', r'tempCodeRunnerFile\.c'
    ]

    delete_files_by_regex(folder, regex_list, ignore)
