public class TrafficController {
	int sem =1;
	public synchronized void enterLeft() {
		try {
			if(sem<=0) {
				wait();
			}
			sem--;
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	
	public synchronized void leaveRight() {
		sem++;
		notify();
		
	}


	
	public synchronized void enterRight() {
		try {
			if(sem<=0) {
				wait();
			}
			sem--;
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public synchronized void leaveLeft() {
		sem++;
		notify();
		
	}

}