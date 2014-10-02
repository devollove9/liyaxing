CPPFLAGS = `wx-config --cppflags` -fopenmp -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP
LDLIBS = `wx-config --libs` -fopenmp
CXX = g++

SOURCES = CApp.cpp CBaseBlackAndWhite.cpp CBaseCanny.cpp CBaseEmboss.cpp \
        CBenchmarkDlg.cpp CBlackAndWhite.cpp CCanny.cpp CDocument.cpp \
        CDocumentObserver.cpp CEmboss.cpp CFrame.cpp \
        CIdDlg.cpp CMoments.cpp CMomentsDlg.cpp CPicture.cpp CProcessingDlg.cpp \
	CProgressCtrl.cpp CProcessor.cpp CTestDlg.cpp CViewEdit.cpp


OBJS = CApp.o CBaseBlackAndWhite.o CBaseCanny.o CBaseEmboss.o \
        CBenchmarkDlg.o CBlackAndWhite.o CCanny.o CDocument.o \
        CDocumentObserver.o CEmboss.o CFrame.o \
        CIdDlg.o CMoments.o CMomentsDlg.o CPicture.o CProcessingDlg.o \
	CProgressCtrl.o CProcessor.o CTestDlg.o CViewEdit.o

all: Images

Images: $(OBJS)
	$(CXX) $^ $(LDLIBS) -o$@

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f *.o *.d
