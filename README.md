Corpus
============

Video Lectures
============

[<img src="https://github.com/StarlangSoftware/Corpus/blob/master/video.jpg" width="50%">](https://youtu.be/xTrdKY5uI08)

For Developers
============
You can also see [Java](https://github.com/starlangsoftware/Corpus), [Python](https://github.com/starlangsoftware/Corpus-Py), [Cython](https://github.com/starlangsoftware/Corpus-Cy), [Swift](https://github.com/starlangsoftware/Corpus-Swift), [Js](https://github.com/starlangsoftware/Corpus-Js), [C++](https://github.com/starlangsoftware/Corpus-CPP), or [C#](https://github.com/starlangsoftware/Corpus-CS) repository.

## Requirements

* [C Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called DataStructure will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/Corpus-C.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run CorpusTest.cpp.

Detailed Description
============

+ [Corpus](#corpus)
+ [TurkishSplitter](#turkishsplitter)

## Corpus

To store a corpus in memory

	Corpus_ptr a = create_corpus("derlem.txt");

If this corpus is split with dots but not in sentences

	Corpus(String fileName, SentenceSplitter sentenceSplitter)

To eliminate the non-Turkish sentences from the corpus

	Corpus_ptr create_corpus3(const char *file_name, bool (*is_valid_word)(const char*))

The number of sentences in the corpus

	int corpus_sentence_count(const Corpus* corpus)

To get ith sentence in the corpus

	Sentence_ptr corpus_get_sentence(const Corpus* corpus, int index)

## TurkishSplitter

TurkishSplitter class is used to split the text into sentences in accordance with the . rules of Turkish.

	Array_list_ptr sentence_split_turkish(const char* line)
