# Uriah's Symmetric Encryption

This encryption is based on the one-time pad encryption method, which, when used once, cannot be cracked

This program takes an ascii key, and divides it to multiple keys using the space char
It then XORs each char from the original message with the key[0][counter++ % key[0].length()], key[1][counter++ % key[1].length()]....

Mathematically, it's just a pseudo-random generator for a one-time pad long xor key,
But the catch about it is that extremely long textual key can be used easily

For example, the Pentagon wants to send a single large message to the Kremlin
It can send a few soldiers with the info, of the algorithm and the short info 'The key is the first two paragraphs of Harry Poter'
When the soldiers come back from the Kremlin to the Pentagon, and this short info is passed securely, they can use this algorithm to encrypt the message with the first two paragraphs of Harry Poter
If the first chapter of Harry Potter is long enough, and this encryption algorithm stays between the two nations,
It may be mathematically impossible to crack this encryption.

In conclusion, this encryption is good only when:
1. There is a secure way to pass this code and short info like 'first two paragraphs of Harry Potter'
2. It is only used once
3. The key is quite long, with multiple spaces and words

While I can't think of use to it now, I think it's still kinda cool

Feel free to try! [here's a download link](https://github.com/UriahShaulMandel/Uriah-s-Symmetric-Encryption/raw/master/Uriah's%20Symmetric%20Encryption.exe)

## Algorithm

![pic](https://github.com/UriahShaulMandel/Uriah-s-Symmetric-Encryption/blob/master/USE.png?raw=true)
