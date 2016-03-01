package sensor.collect;

public class test {
	private static final String USER_NAME = "zhangdaishuai1";
	private static final String PASSWORD = "zhangdaishuai1";
	private static final String SPACE = "securitySpace";
	private static final String THEME = "securityTheme";
	private static MimoNodeAPI mimonode;

	public static void main(String[] args) {
		// mimonode = new MimoNodeAPI();
		login();

		// for(int i=0;i<1;i++){
//		 myPublish();
		mySub();
//		myget();
		
		
		// }
		// mimonode.logout();
	}

	public static void login() {

		MimoNodeAPI mimonode = new MimoNodeAPI();

		// mimonode.login("55715c7b992364270bcfa69a", "a", new Callback() {
		mimonode.login(USER_NAME, PASSWORD, new Callback() {
			public void successCallback(Object message) {
				System.out.println("authSucceed: " + message);
			}

			public void errorCallback(Object message) {
				System.out.println("authFailed: " + message);
			}

			public void connectCallback() {
				System.out.println("connected:");
			}

			public void disconnectCallback() {
				System.out.println("disconnect:");
			}

			public void socketErrorCallback(Object error) {
				System.out.println("socketError: " + error);
			}

			public void newMessageCallback(Object message) {
				System.out.println("newMessage: " + message);
			}
		});

	}

	public static void myPublish() {
		MimoNodeAPI mimonode = new MimoNodeAPI();

		mimonode.publishOnTheme("PM2.5", "8ws", "157","1414", USER_NAME,// userName
				SPACE,// spaceName
				THEME,// themeName

				new Callback() {
					public void successCallback(Object message) {
						System.out.println("publishOnTheme: " + message);
					}

					public void errorCallback(Object message) {
						System.out.println("publishOnTheme: " + message);
					}
				});
	}
	
/*	public static void myget() {
		MimoNodeAPI mimonode = new MimoNodeAPI();

		mimonode.getStoredMessages( USER_NAME,// userName
				new Callback() {
					public void successCallback(Object message) {
						System.out.println("getStoredMessages: " + message);
					}

					public void errorCallback(Object message) {
						System.out.println("getStoredMessages: " + message);
					}
				});
	}
*/
	public static void mySub() {
		MimoNodeAPI mimonode = new MimoNodeAPI();

		mimonode.subscribeOnTheme(USER_NAME, SPACE, THEME,

		new Callback() {
			public void successCallback(Object message) {
				System.out.println("sub: " + message);
			}

			public void errorCallback(Object message) {
				System.out.println("sub: " + message);
			}
			
		});

	}
}