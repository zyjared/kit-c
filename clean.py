import os
import re


def delete_files_by_regex(folder_path, regex_list, root_folder_path='.'):
    for filename in os.listdir(folder_path):
        if os.path.isdir(os.path.join(folder_path, filename)):
            delete_files_by_regex(os.path.join(
                folder_path, filename), regex_list, root_folder_path)

        file_path = os.path.join(folder_path, filename)
        relative_path = os.path.relpath(file_path, root_folder_path)
        for regex_pattern in regex_list:
            if re.search(regex_pattern, filename):
                try:
                    os.remove(file_path)
                    print(f"Deleted: {relative_path}")
                except OSError as e:
                    print(f"Error deleting {relative_path}: {e}")


if __name__ == "__main__":

    if len(os.sys.argv) > 1:
        folder = os.sys.argv[1]
    else:
        folder = '.'

    regex_list = [
        r'.*\.(exe|EXE|dat|DAT)$', r'tempCodeRunnerFile\.c'
    ]

    delete_files_by_regex(folder, regex_list)
