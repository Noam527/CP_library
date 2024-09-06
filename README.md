# Competitive Programming Library
Following are implementations of algorithms, data structures and other techniques, written by me or by 3rd party.<br>
Every implementation aims for:
- Readability: as much as possible and convenient, so that diving into the code will not be tedious, with proper comments.
- Compactness: shorter implementations are better, as this will also be used in an ICPC notebook.
- Being Generic: usually in data structures, support for as much as the abstract data structure allows - supporting both minimum and maximum operations, int vs long long, templates.

With this in mind, there must be criteria that all implementations must satisfy - these are the following:
- **Efficiency**: The most obvious requirement - must be implemented efficiently in terms of running time and memory consumption. Improving constant factors is also important.
- **Implementation specific details**: Surrounded by / are next to comments containing the letters `IMP`, or are described properly at the top of the file.
- **Documentation**: Outside of the code file, some explanation required to understand it enough to allow entry into the code / understanding the idea. The sufficiency of the explanation is subjective to what I feel like is both concise and enough. This will be provided as a README file.


## Documentation Format
Each entry will have a documentation file that gives sufficient and concise information regarding the problem being solved and the idea. This also has a format:

- **Problem Statement**: The problem that is solved by this algorithm / data structure.
- **Time and memory complexities**: Time and memory complexities. Amortization and high constant factors will also be mentioned.
- **Core Ideas**: This is a subjective section - whichever explanation of the algorithm that feels the most natural, concise and convincing to me.
- **Testing**: Mention if this was tested on some online judge / benchmarked, and its performence.
- **Source**: If it's 3rd party or inspired by 3rd party, this will link to it.


## Optionals
Each entry can also have one of the following optional things:
- Specific applications or implementations for specific common needs.
- Extensions and usages of the data structure.