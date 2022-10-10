/*
Guia0114 - v0.0. - 14 / 08 / 2022
Author: Lara Brigida Rezende Souza

Para compilar em uma janela de comandos (terminal):
No Linux : g++ -o Guia0114 ./Guia0114.cpp
No Windows: g++ -o Guia0114.exe Guia0114.cpp

Para executar em uma janela de comandos (terminal):
No Linux : ./Guia0114
No Windows: Guia0114
*/

// lista de dependencias
#include "karel.hpp"

// --------------------------- definicoes de metodos
/**
decorateWorld - Metodo para preparar o cenario.
@param fileName - nome do arquivo para guardar a descricao.
*/
void decorateWorld ( const char* fileName )
{
	// colocar paredes no mundo
	world->set ( 3, 6, HWALL ); // horizontal
	world->set ( 4, 6, HWALL ); // horizontal
	world->set ( 5, 6, HWALL ); // horizontal
	world->set ( 6, 6, HWALL ); // horizontal
	world->set ( 3, 2, HWALL ); // horizontal
	world->set ( 4, 2, HWALL ); // horizontal
	world->set ( 5, 2, HWALL ); // horizontal
	world->set ( 6, 2, HWALL ); // horizontal
	world->set ( 2, 6, VWALL ); // vertical
	world->set ( 2, 5, VWALL ); // vertical
	world->set ( 2, 4, VWALL ); // vertical
	world->set ( 2, 3, VWALL ); // vertical
	world->set ( 6, 3, VWALL ); // vertical
	world->set ( 6, 4, VWALL ); // vertical
	world->set ( 6, 5, VWALL ); // vertical
	// colocar um marcador no mundo
	world->set ( 2, 6, BEEPER );
	world->set ( 6, 7, BEEPER );
	world->set ( 7, 3, BEEPER );
	// salvar a configuracao atual do mundo
	world->save( fileName );
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
	turnRight - Procedimento (acao) para virar 'a direita.
	*/
	void turnRight ( )
	{
		// testar se o robo esta' ativo
		if ( checkStatus ( ) )
		{
			// o agente que executar esse metodo
			// devera' virar tres vezes 'a esquerda
			turnLeft ( );
			turnLeft ( );
			turnLeft ( );
		} // end if
	} // end turnRight ( )

	/**
	moveN - Metodo para mover certa quantidade de passos.
	@param steps - passos a serem dados.
	*/
	void moveN( int steps )
	{
		// definir dado local
		int step = 0;
		// repetir contando e testando ate' atingir a quantidade de passos
		for ( step = 1; step <= steps; step = step + 1 ) // outra forma de repetir
		{
			// dar um passo por vez
			move( );
		} // end if
	} // end moveN( )

	/**
	doPartialTask - Metodo para descrever parte de uma tarefa.
	*/
	void doPartialTask( )
	{
		// especificar acoes dessa parte da tarefa
		moveN( 6 );
		turnLeft( );
		moveN(2);
		pickBeeper();
		moveN(4);
		turnLeft();
		moveN(1);
		pickBeeper();
		moveN(4);
		turnLeft();
		moveN(1);
		pickBeeper();
		turnRight();
		turnRight();
		moveN(1);
		turnRight();
		moveN(5);
		turnRight();
		moveN(1);
		turnRight();
		moveN(3);
		turnLeft();
		moveN(3);
		putBeeper();
		turnLeft();
		moveN(2);
		turnLeft();
		moveN(3);
		turnRight();
		moveN(1);
		turnRight();
		moveN(5);
		turnRight();
		moveN(6);
		turnRight();
		turnRight();
		turnOff();
	} // end doPartialTask( )

	/**
	doTask - Relacao de acoes para o robo executar.
	*/
	void doTask( )
	{
		// especificar acoes da tarefa
		doPartialTask( );
		doPartialTask( );
		// testar se ha' marcador antes ...
		if ( nextToABeeper( ) )
		{
			// ... de tentar carrega-lo
			pickBeeper( );
		} // end if
		doPartialTask( );
		// testar se carrega marcador antes ...
		if ( nbeepers( ) > 0 )
		{
			// ... de tentar descarrega-lo
			putBeeper( );
		} // end if
		doPartialTask( );
		turnLeft( );
		// encerrar
		turnOff ( );
	} // end doTask( )
}; // end class MyRobot

// --------------------------- acao principal
/**
Acao principal: executar a tarefa descrita acima.
*/
int main ( )
{
	// definir o contexto
	// criar o ambiente e decorar com objetos
	// OBS.: executar pelo menos uma vez,
	// antes de qualquer outra coisa
	// (depois de criado, podera' ser comentado)
	world->create ( "" ); // criar o mundo
	decorateWorld ( "Guia0114.txt" );
	world->show ( );
	// preparar o ambiente para uso
	world->reset ( ); // limpar configuracoes
	world->read ( "Guia0114.txt" );// ler configuracao atual para o ambiente
	world->show ( ); // mostrar a configuracao atual
	set_Speed ( 3 ); // definir velocidade padrao
	// criar robo
	MyRobot *robot = new MyRobot( );
	// posicionar robo no ambiente (situacao inicial):
	// posicao(x=1,y=1), voltado para direita, com zero marcadores, nome escolhido )
	robot->create ( 1, 1, EAST, 0, "Karel" );
	// executar tarefa
	robot->doTask ( );
	// encerrar operacoes no ambiente
	world->close ( );
	// encerrar programa
	getchar ( );
	return ( 0 );
} // end main ( )

// ---------------------------------------------- testes
/*
---------------------------------------------- documentacao complementar
---------------------------------------------- notas / observacoes / comentarios
---------------------------------------------- previsao de testes
---------------------------------------------- historico
*/
