package sensor.collect;

/**
 * mimonode APIs for Java Applications.
 *
 * @author mimonode by xufei
 * 
 * @version v2.0
 * 
 * @data 2015.12.06
 */

import java.net.URISyntaxException;
import org.json.*;
import com.github.nkzawa.emitter.*;
import com.github.nkzawa.socketio.client.*;

public class MimoNodeAPI {

	private static Socket socket;

	/**
	 * This function is used to connect the mimonode server.
	 * 
	 * @param callback
	 */
	private void connect(final Callback callback) {
		try {
			socket = IO.socket("http://10.107.29.248:3002/access");
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}

		socket.on(Socket.EVENT_CONNECT, new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.connectCallback();
			}
		}).on(Socket.EVENT_DISCONNECT, new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.disconnectCallback();
			}
		}).on(Socket.EVENT_ERROR, new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.socketErrorCallback(args[0]);
			}
		});
		socket.connect();
	};

	/**
	 * This function is used to register an account in mimonode.
	 * 
	 * @param userName
	 *            , password, email, callback.
	 * 
	 * @see successCallback,errorCallback,connectCallback,disconnectCallback,
	 *      socketErrorCallback are supposed to Override in this callback.
	 */
	public void register(String userName, String password, String email,
			final Callback callback) {

		this.connect(callback);
		JSONObject userData = new JSONObject();
		try {
			userData.put("userName", userName);
			userData.put("password", password);
			userData.put("email", email);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("register", userData)
				.on("registerSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("registerFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to login mimonode. new messages are accepted from
	 * now on if there are any messages.
	 * 
	 * @param userName
	 *            , password, email, callback.
	 * 
	 * @see successCallback, errorCallback, connectCallback, disconnectCallback,
	 *      socketErrorCallback, NewMessageCallback are supposed to Override in
	 *      this callback.
	 */
	public void login(String userName, String password, final Callback callback) {

		this.connect(callback);
		socket.on("newMessages", new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.newMessageCallback((JSONObject) args[0]);
			}
		});

		JSONObject userData = new JSONObject();
		try {
			userData.put("userName", userName);
			userData.put("password", password);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("auth", userData).on("authSucceed", new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.successCallback((JSONObject) args[0]);
			}
		}).on("authFailed", new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.errorCallback(args[0]);
			}
		});
	};

	/**
	 * This function is used to logout from mimonode. new messages won't be
	 * accepted until next login succeed.
	 * 
	 * @param
	 */
	public void logout() {
		socket.disconnect();
	}

	/**
	 * This function is used to createSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceName, spaceType, algorithmType, privacy, secureLevel,
	 *            defaultPermission, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createSpace(String userName, String spaceName,final Callback callback) {

		JSONObject space = new JSONObject();
		try {
			space.put("rootSpaceName", spaceName);
			space.put("owner", userName);
//			space.pubers=userName;
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("createSpace", space)
				.on("createSpaceSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("createSpaceFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to createThemeOnSpace in mimonode.
	 * 
	 * @param owner
	 *            , spaceId, themeName, themeType, algorithmType, privacy,
	 *            secureLevel, defaultPermission, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void createThemeOnSpace(String userName, String spaceName,
			String themeName, final Callback callback) {

		JSONObject space = new JSONObject();
		JSONObject theme = new JSONObject();
		try {
			space.put("rootSpaceName", spaceName);
			theme.put("owner", userName);
			theme.put("pubers",userName);
			theme.put("subSpaceName",themeName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("createThemeOnSpace", space)
				.on("createThemeOnSpaceSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("createThemeOnSpaceFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to subscribeOnTheme in mimonode.
	 * 
	 * @param subscriberId
	 *            , spaceId, themeId, attrName1, subValue11, attrName2,
	 *            subValue21, subValue22, attrName3, subValue31, subValue32,
	 *            callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribeOnTheme(String userName, String spaceName,
			String themeName, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("rootSpaceName", spaceName);
			data.put("subSpaceName", themeName);
			data.put("subscriber", userName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("subscribeOnTheme", data)
				.on("subscribeOnThemeSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("subscribeOnThemeFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to publishOnTheme in mimonode.
	 * 
	 * @param publisherId
	 *            , spaceId, themeId, secureLevel, msgType, content, attrName1,
	 *            value11, attrName2, value2, attrName3, value3, callback.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publishOnTheme(String sensorId,String monitorContent,String concentrationvalue,String time,String userName, String spaceName,
			String themeName, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("rootSpaceName", spaceName);
			data.put("subSpaceName", themeName);
			data.put("puber", userName);
			data.put("sensorId", sensorId);
			data.put("monitorContent", monitorContent);
			data.put("concentration", concentrationvalue);
			data.put("monitorTime", time);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("publishOnTheme", data)
				.on("publishOnThemeSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("publishOnThemeFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

}