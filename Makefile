#Inicia valores iniciais
EXE				:= proj #Nome do executável
CC				:= g++ #Compilador
MAIN_SRC	:= main.cpp
H_SRC			:=  postgres.h aluno.h requerimento.h gerenciamento.h#Adicionar arquivos .h aqui
CFLAGS			:= -Wall -g 
LDFLAGS			:= -lpqxx -lpq

#Define variável com arquivos .o
MAIN_OBJ	:= $(MAIN_SRC:.cpp=.o)
OBJS		:= $(H_SRC:.h=.o)

#Junta tudo em um executável
all: output

output:$(MAIN_OBJ) $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $(EXE)
#$@ pega o nome do target(output)
#$^ para listar todos os pré-requisitos do target

#Cria main.o
$(MAIN_OBJ): $(MAIN_SRC) $(H_SRC)
	$(CC) $< $(CFLAGS) -c 
#$< pega o nome do primeiro pré-requisito

#Cria demais arquivos .o
#% pega o tronco do nome
%.o: %.$(EXT) %.h
	$(CC) $< $(CFLAGS) -c

#Apaga arquivos .o e executavel
clean:
	rm -f *.o $(EXE)