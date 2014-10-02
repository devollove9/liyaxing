void app::split() {

    string test = "this is my testing string.";

    char* tempLine = new char[test.size() + 1];
    strcpy(tempLine, test.c_str());

    char* singleWord;

    for (int i = 0; i < sizeof(tempLine); i++) {

        if (tempLine[i] == ' ') {
            words[wordCount] = singleWord;
            delete[]singleWord;
        }

            else {
            singleWord[i] = tempLine[i];
            wordCount++;

            }

    }

    cout << words[0];
    delete[]tempLine;

}
