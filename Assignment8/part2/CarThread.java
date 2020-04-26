import java.lang.Thread;
import java.util.*;

public class CarThread extends Thread {
	
	//RaceTrack gui;
	int carIndex;

	public CarThread(/* RaceTrack gui, */int carIndex){
		//this.gui = gui;
		this.carIndex = carIndex;
	}	

	public void moveCar(int distance){
		System.out.println("Car #"+carIndex+" moved " + distance+"!");
	}

	public void run(){

		// car moves bt 0-10px
		int max = 10;
		int min = 0;

		try{
			while(true){
				int distance = (int) (Math.random() * ((max - min) +1) + min );
	
				moveCar(distance);
				sleep(2000); // change to 50
			}
		} catch (InterruptedException e){
			System.out.println("Stopped Car #" + carIndex + "!");
		}

	}

	public static void main(String[] args){

		CarThread car1 = new CarThread(1);
		CarThread car2 = new CarThread(2);

		car1.start();
		car2.start();
	}


}