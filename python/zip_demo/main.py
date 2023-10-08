import os
import zipfile
import tarfile


def zip_dir(target_path, output_path):
    """
    压缩指定文件夹
    :param dirpath: 目标文件夹路径
    :param outFullName:
    :return: 无
    """
    zip = zipfile.ZipFile(output_path, "w", zipfile.ZIP_DEFLATED)
    for path, dirnames, filenames in os.walk(target_path):
        fpath = path.replace(target_path, '')  # 去掉目标跟路径，只对目标文件夹下边的文件及文件夹进行压缩
        for filename in filenames:
            zip.write(os.path.join(path, filename), os.path.join(fpath, filename))
    zip.close()

    return None


def tar_dir(target_path, output_path):
    """
    压缩指定文件
    :param target_path: 目标文件
    :param output_path: 输出路径
    :return: None
    """
    with tarfile.open(output_path, "w:gz") as tar:
        tar.add(target_path, arcname=os.path.basename(target_path))
    return None


if __name__ == '__main__':
    print("Zip")
    # zip_dir("/opt/file/bags", "hahaha.zip")
    zip_dir("/opt/file/bags", "hahaha.tar.gz")
