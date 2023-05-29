cmake_minimum_required(VERSION 3.23)
project(Corpus C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Corpus src/WordFormat.h src/FileDescription.c src/FileDescription.h src/Sentence.h src/Sentence.c src/Paragraph.c src/Paragraph.h src/CorpusStream.c src/CorpusStream.h src/Corpus.c src/Corpus.h src/TurkishChecker.c src/TurkishChecker.h src/SentenceSplitter.h src/SentenceSplitter.c src/TurkishSplitter.c src/TurkishSplitter.h src/EnglishSplitter.c src/EnglishSplitter.h)
target_link_libraries(Corpus ${CONAN_LIBS})
