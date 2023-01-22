/*
	Guia_0211 - v0.0. - 20 / 08 / 2022
	Author: Lara Brigida Rezende Souza

	Para compilar em uma janela de comandos (terminal):
	No Linux : g++ -o Guia0211 ./Guia0211.cpp
	No Windows: g++ -o Guia0211.exe Guia0211.cpp

	Para executar em uma janela de comandos (terminal):
	No Linux : ./Guia0211
	No Windows: Guia0211
*/

// lista de dependencias
#include "karel.hpp"

// --------------------------- definicoes de metodos
/**
	decorateWorld - Metodo para preparar o cenario.
	@param fileName - nome do arquivo para guardar a descricao.
*/
void decorateWorld(const char *fileName) 
{
	// colocar paredes no mundo
	world->set(2, 1, VWALL);
	world->set(3, 2, VWALL);
	world->set(4, 3, VWALL);
	world->set(6, 3, VWALL);
	world->set(7, 2, VWALL);
	world->set(8, 1, VWALL);
	world->set(3, 1, HWALL);
	world->set(4, 2, HWALL);
	world->set(5, 3, HWALL);
	world->set(6, 3, HWALL);
	world->set(7, 2, HWALL);
	world->set(8, 1, HWALL);

	// colocar um marcador no mundo
	world->set(7, 3, BEEPER);
	world->set(7, 3, BEEPER);
	world->set(7, 3, BEEPER);
	world->set(8, 2, BEEPER);
	world->set(8, 2, BEEPER);
	world->set(9, 1, BEEPER);
	
	// salvar a configuracao atual do mundo
	world->save(fileName);
} // decorateWorld ( )

/**
	Classe para definir robo particular (MyRobot),
	a partir do modelo generico (Robot)
	Nota: Todas as definicoes irao valer para qualquer outro robo
	criado a partir dessa nova descricao de modelo.
*/
class MyRobot : public Robot 
{
	public:
		/**
			turnRight - Procedimento para virar 'a direita.
		*/
		void turnRight() 
		{
			// definir dado local
			int step = 0;
			
			// testar se o robo esta' ativo
			if (checkStatus()) 
			{
				// o agente que executar esse metodo
				// devera' virar tres vezes 'a esquerda
				for (step = 1; step <= 3; step = step + 1) 
				{
					turnLeft();
				} // end for
			}   // end if
		}     // end turnRight ( )

		/**
			moveN - Metodo para mover certa quantidade de passos.
			@param steps - passos a serem dados.
		*/
		void moveN(int steps) 
		{
			// definir dado local
			int step = 0;
			
			// testar se a quantidade de passos e' maior que zero
			for (step = steps; step > 0; step = step - 1) 
			{
				// dar um passo
			move();
			} // end if
		}   // end moveN( )

		/*
			stepUpRight - Procedimento para csubir a escada 'a direita
		*/
		void stepUpRight() 
		{
			// acoes para subir um degrau
			moveN(1);
			turnRight();
			moveN(1);
			turnLeft();
		} // fim stepUpRight( )

		/*
			stepUpLeft - Procedimento para csubir a escada 'a direita
		*/
		void stepUpLeft()
		{
			// acoes para subir um degrau
			moveN(1);
			turnLeft();
			moveN(1);
			turnRight();
		} // fim stepUpLeft( )

		/*
			stepDownRight - Procedimento para csubir a escada 'a direita
		*/
		void stepDownRight() 
		{
			// acoes para subir um degrau
			moveN(1);
			turnRight();
			moveN(1);
			turnLeft();
		} // fim stepDownRight( )

		/*
			stepDownLeft - Procedimento para csubir a escada 'a direita
		*/
		void stepDownLeft() 
		{
			// acoes para subir um degrau
			moveN(1);
			turnLeft();
			moveN(1);
			turnRight();
		} // fim stepDownLeft( )

		/**
			doPartialTask - Metodo para especificar parte de uma tarefa.
		*/
		void doPartialTask() 
		{
			// especificar acoes dessa parte da tarefa
			moveN(1);
			turnLeft();
			stepUpRight();
			stepUpRight();
			stepUpRight();
			turnRight();
			moveN(1);
			stepDownRight();
			pickBeeper();
			pickBeeper();
			pickBeeper();
			stepDownRight();
			pickBeeper();
			pickBeeper();
			stepDownRight();
			pickBeeper();
			turnLeft();
			stepUpLeft();
			stepUpLeft();
			stepUpLeft();
			turnLeft();
			moveN(1);
			stepDownLeft();
			putBeeper();
			putBeeper();
			putBeeper();
			stepDownLeft();
			putBeeper();
			putBeeper();
			stepDownLeft();
			putBeeper();
			moveN(1);
			turnRight();
			turnRight();
			turnOff();
		} // end doPartialTask( )

		/**
			doTask - Relacao de acoes para o robo executar.
		*/
		void doTask() 
		{
			// definir dado local
			int step = 4;
			
			// especificar acoes da tarefa
			while (step > 0) 
			{
				// realizar uma parte da tarefa
				doPartialTask();
				
				// tentar passar 'a proxima
				step = step - 1;
			} // end while
			// encerrar
			turnOff();
		} // end doTask( )
};  // end class MyRobot

// --------------------------- acao principal
/**
	Acao principal: executar a tarefa descrita acima.
*/
int main()
{
	// definir o contexto
	// criar o ambiente e decorar com objetos
	// OBS.: executar pelo menos uma vez,
	// antes de qualquer outra coisa
	// (depois de criado, podera' ser comentado)
	world->create(""); // criar o mundo
	decorateWorld("Guia0211.txt");
	world->show();
	
	// preparar o ambiente para uso
	world->reset();              // limpar configuracoes
	world->read("Guia0211.txt"); // ler configuracao atual para o ambiente
	world->show();               // mostrar a configuracao atual
	set_Speed(3);                // definir velocidade padrao
	
	// criar robo
	MyRobot *robot = new MyRobot();
	
	// posicionar robo no ambiente (situacao inicial):
	// posicao(x=1,y=1), voltado para direita, com zero marcadores, nome escolhido
	// )
	robot->create(1, 1, EAST, 0, "Karel");
	
	// executar tarefa
	robot->doTask();
	
	// encerrar operacoes no ambiente
	world->close();
	
	// encerrar programa
	getchar();
	
	return (0);
} // end main ( )

// -------------------------------------------- testes
/*
	---------------------------------------------- documentacao complementar
	---------------------------------------------- notas / observacoes / comentarios
	---------------------------------------------- previsao de testes
	---------------------------------------------- historico
	Versao Data Modificacao
	0.1 21/08 esboco
  */
