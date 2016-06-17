package com.syh.pubjson;

/**
 * mimonode APIs for Java Applications.
 *
 * @author mimonode by xufei, zgwang
 * 
 * @version v2.0
 * 
 * @data 2016.5.30
 */

import java.net.URISyntaxException;
import org.json.*;

import android.util.Log;

import com.github.nkzawa.emitter.*;
import com.github.nkzawa.socketio.client.*;

public class MimoNodeAPI {

	private static final String TAG = "MimoNode";
	private static Socket socket;

	/**
	 * This function is used to connect the mimonode server.
	 * 
	 * @param callback
	 */
	private void connect(final Callback callback) {
		try {
			socket = IO.socket("http://10.107.29.248:8888/access");
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
	 * @param userName, password, email, callback.
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
	 * This function is used to update an account in mimonode.
	 * 
	 * @param userName, password, email, callback.
	 * 
	 * @see successCallback,errorCallback,connectCallback,disconnectCallback,
	 *      socketErrorCallback are supposed to Override in this callback.
	 */
	public void updateUser(String userName, String password, String email,
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
		socket.emit("updateUser", userData)
				.on("updateUserSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("updateUserFailed", new Emitter.Listener() {
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
	 * @param userName, password, callback.
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
/****************************************�ݲ�����******************************************/   
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
			// space.pubers=userName;
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
/******************************************************************************************/
	/**
	 * This function is used to subscribe in mimonode.
	 * 
	 * @param rootSpaceName, subSpaceName, userName.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void subscribe(String userName, String rootSpaceName, 
			String subSpaceName, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("rootSpaceName", rootSpaceName);
			data.put("subSpaceName", subSpaceName);
			data.put("suberName", userName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("subscribe", data)
				.on("subscribeSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("subscribeFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};

	/**
	 * This function is used to unsubscribe in mimonode.
	 * 
	 * @param rootSpaceName, subSpaceName, userName.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void unsubscribe(String userName, String rootSpaceName, 
			String subSpaceName, final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("rootSpaceName", rootSpaceName);
			data.put("subSpaceName", subSpaceName);
			data.put("suberName", userName);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("unsubscribe", data)
				.on("unsubscribeSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("unsubscribeFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};
	
	/**
	 * This function is used to publish in mimonode.
	 * 
	 * @param rootSpaceName, subSpaceName, puber, sensorId, monitorContent, 
	 * concentration, monitorTime.
	 * 
	 * @see successCallback, errorCallback are supposed to Override in this
	 *      callback.
	 */
	public void publish(String rootSpaceName, String subSpaceName, 
			String userName, String nameofAPI, String numberofAPI,
			String threadIDofAPI, String timeofAPI, String processID,
			String IMEI, String contextofAPI, String FatherThreadIdofAPI,
			String SonThreadIdofAPI, String resultofAPI,String packageNameofAPI,final Callback callback) {

		JSONObject data = new JSONObject();
		try {
			data.put("rootSpaceName", rootSpaceName);
			data.put("subSpaceName", subSpaceName);
			data.put("puber", userName);
			data.put("nameofAPI", nameofAPI);
			data.put("numberofAPI", numberofAPI);
			data.put("threadIDofAPI", threadIDofAPI);
			data.put("timeofAPI", timeofAPI);
			data.put("processID", processID);
			data.put("IMEI", IMEI);
			data.put("contextofAPI", contextofAPI);
			data.put("FatherThreadIdofAPI", FatherThreadIdofAPI);
			data.put("SonThreadIdofAPI", SonThreadIdofAPI);
			data.put("resultofAPI", resultofAPI);
			data.put("packageNameofAPI", packageNameofAPI);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		socket.emit("publish", data)
				.on("publishSucceed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.successCallback((JSONObject) args[0]);
					}
				}).on("publishFailed", new Emitter.Listener() {
					@Override
					public void call(Object... args) {
						callback.errorCallback((JSONObject) args[0]);
					}
				});
	};
	
	public void publish(String rootSpaceName, String subSpaceName, 
			String userName, JSONObject data, final Callback callback) {
		try {
			data.put("rootSpaceName", rootSpaceName);
			data.put("subSpaceName", subSpaceName);
			data.put("puber", userName);
			data.put("puber", userName);		
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Log.v(TAG, "发送json： " + data.toString());
		socket.emit("publish", data)
		.on("publishSucceed", new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.successCallback((JSONObject) args[0]);
				// System.out.println("publishOnTheme: " + (JSONObject)
				// args[0]);
			}
		}).on("publishOnThemeFailed", new Emitter.Listener() {
			@Override
			public void call(Object... args) {
				callback.errorCallback((JSONObject) args[0]);
			}
		});
	}

}
