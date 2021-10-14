# Bittorrent like Protocol

Communication protocol for peer to peer file transfer and sharing, which enables users to distribure data and electronic files over internet in a de-centralized manner, To send or recieve, a person uses a torrent client on the internet connected computer.

It uses merkle trees to detect and correct data that was corrupted during the data transfer. The torrent files contains the metadata which contains the entire merkle tree. This way, The data recieved is verfied with the merkle tree that is present in the torrent file.

The data tha is sent is also compressed with huffman encoding in roder to reduce the bandwidth used.