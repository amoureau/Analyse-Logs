CXX = g++
CXXFLAGS = -O3 -I.
OBJDIR = objets

DEPS = Lecture.h Affichage.h Stats.h
OBJ = $(patsubst %,$(OBJDIR)/%,Lecture.o Affichage.o Stats.o main.o)

$(OBJDIR)/%.o: %.cpp $(DEPS)
	mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

analog: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o analog