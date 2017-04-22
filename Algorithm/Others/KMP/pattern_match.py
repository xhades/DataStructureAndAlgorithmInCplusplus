# -*- coding: utf-8 -*-
import argparse
import ctypes

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--pattern', help='string pattern')
    parser.add_argument('-d', '--document', help='document')
    args = parser.parse_args()

    pattern = args.pattern
    document_dir = args.document

    fd = open(document_dir)
    document = fd.read()
    fd.close()

    lib = ctypes.cdll.LoadLibrary('libkmp.so')
    pattern = ctypes.create_string_buffer(bytes(pattern.encode('utf8')))
    document = ctypes.create_string_buffer(bytes(document.encode('utf8')))
    lib.match(pattern, document)

if __name__ == '__main__':
    main()
