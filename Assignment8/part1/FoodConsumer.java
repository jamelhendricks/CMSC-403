import java.util.*;
import java.lang.Thread;

public class FoodConsumer extends Thread {
	
	FoodBank bank;
	
	public FoodConsumer(FoodBank initBank){
		this.bank = initBank;
	}
	
	
	
	@Override
	public void run(){
		int max = 100;
		int min = 1;
		


		while(true){
			int foodSubtraction = (int) (Math.random() * ((max - min) +1) + min );
				
			bank.takeFood(foodSubtraction);
			try {
				Thread.sleep(600);
			} catch (InterruptedException e){
				System.out.println("Interrupted! Did not sleep(100)!");
			}
		}
		

	}
	
	
}