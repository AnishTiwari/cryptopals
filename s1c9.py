def pad(block, block_size):
    if len(block) == block_size:
        return block
    pads =   block_size - len(block)
    blok = [b for b in block]
    for i in range (0,pads):
        blok.append(pads)
    return bytes(blok)

def main():
    string = b'YELLOW SUBMARINE'
    print(pad(string,20))

if __name__ == "__main__":
    main()
