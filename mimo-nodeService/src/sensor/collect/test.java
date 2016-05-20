package sensor.collect;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.json.JSONObject;

public class test {
	private static final String USER_NAME = "zhangdaishuai1";
	private static final String PASSWORD = "zhangdaishuai1";
	private static final String SPACE = "securitySpace";
	private static final String THEME = "securityTheme";
	private static MimoNodeAPI mimonode = new MimoNodeAPI();
	private static final SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");// 设置日期格式

	public static void main(String[] args) {
		login();
		mySub();
	}

	public static void saveToFile(JSONObject jo) {
		FileOutputStream fos = null;
		PrintStream ps = null;
		try {
			String fileName = "/home/zds/debug/mimoderver.txt";
			// fos = context.openFileOutput(fileName, Context.MODE_APPEND);
			fos = new FileOutputStream(fileName, true);
			ps = new PrintStream(fos);
			ps.println(jo.toString());
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		} finally {
			try {
				if (ps != null) {
					ps.close();
				}
				if (fos != null) {
					fos.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	public static void login() {

		MimoNodeAPI mimonode = new MimoNodeAPI();

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
				saveToFile((JSONObject) message);
				System.out.println("newMessage: " + df.format(new Date()));

			}
		});

	}

	// 测试例，数据自拟
	public static void myPublish() {
		MimoNodeAPI mimonode = new MimoNodeAPI();

		mimonode.publishOnTheme("PM2.5", "8ws", "157", "1414", USER_NAME,// userName
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