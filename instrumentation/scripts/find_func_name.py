def find_func_name(file_name):
    """
    Extracts the name of the function is tested by a Jotai benchmark file.

    Args:
        file_name (str): Jotai file name.

    Returns:
        str: Name of the function that is implemented in that file.

    Example:
        >>> find_func_name('foo.c_bar.c')
        'bar'
    """

    start = file_name.find('.h_')
    if start == -1:
        start = file_name.find('.c_')
    
    return file_name[start + 3 : -2]