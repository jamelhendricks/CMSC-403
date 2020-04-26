import java.lang.Thread;
import java.util.*;

public class CarThread extends Thread {
	
	RaceTrack gui;
	int carIndex;
	int position = 0;

	public CarThread(RaceTrack gui, int carIndex){
		this.gui = gui;
		this.carIndex = carIndex;
	}	

	public void run(){

		// car moves bt 0-10px
		int max = 10;
		int min = 0;

		try{
			while(!gui.winner){
				int distance = (int) (Math.random() * ((max - min) +1) + min );
				position += distance;
				gui.moveCar(carIndex, position);
				sleep(0);
			}
		} catch (InterruptedException e){
			System.out.println("Stopped Car #" + carIndex + "!");
		}

	}


}