cmake_minimum_required(VERSION 3.23)
project(Corpus)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(regular_c REQUIRED)

add_library(Corpus WordFormat.h FileDescription.c FileDescription.h Sentence.h Sentence.c Paragraph.c Paragraph.h CorpusStream.c CorpusStream.h Corpus.c Corpus.h TurkishChecker.c TurkishChecker.h SentenceSplitter.h SentenceSplitter.c TurkishSplitter.c TurkishSplitter.h EnglishSplitter.c EnglishSplitter.h)
target_link_libraries(Corpus regular_c::regular_c)
