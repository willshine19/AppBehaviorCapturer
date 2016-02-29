package sensor.collect;

/**
 * Abstract class to be subclassed by objects being passed as callbacks to
 * mimonode APIs Default implementation for all methods is blank
 *
 * @author mimonode
 *
 */
public abstract class Callback {

    /**
     * This callback will be invoked when a message is received on the channel
     *
     * @param message
     *            Message
     *
     */
    public void successCallback( Object message) {

    }

    /**
     * This callback will be invoked when an error occurs
     *
     * @param message
     *            Message
     */
    public void errorCallback(Object message) {

    }

    /**
     * This callback will be invoked on getting connected to a channel
     */
    public void connectCallback() {
    }

    /**
     * This callback is invoked on getting reconnected to a channel after
     * getting disconnected
     *
     */
    public void reconnectCallback() {
    }

    /**
     * This callback is invoked on getting disconnected from a channel
     */
    public void disconnectCallback() {
    }

    /**
     * This callback is invoked on getting getting message from a channel
     *
     * @param message
     *            Message
     */
	public void newMessageCallback(Object object) {
	
	}

    /**
     * This callback is invoked on getting an error  from the socket
     *
     * @param message
     *            Message
     */
	public void socketErrorCallback(Object object) {
		
	}

}