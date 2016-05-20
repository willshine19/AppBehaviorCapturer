/**
 * 读取.cpp文件，生成ApiHookerManager.cpp中的内容
 */
package testauto;

import java.io.*;
import java.util.Arrays;

public class readC {
	public static void geth(String name, final String arg) {
		File path = new File("/home/zds/file/" + name);
		MyFilter filter = new MyFilter(arg);
		String[] list = path.list(filter);
		Arrays.sort(list, String.CASE_INSENSITIVE_ORDER);
		for (String dirItem : list) {
			// System.out.println(dirItem);
			// new
			// saveToFile().saveToFile("include","#include \"../ApiHooker/Androidapi/"+dirItem+"\"");
			try {
				read(path.toString() + "/" + dirItem);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	public static void read(String filename) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader(filename));
		String s;
		String name = "", name1 = "", des = "", name0 = "", shorty = "";
		saveToFile ff = new saveToFile();
		while ((s = in.readLine()) != null) {
//			System.out.println(s);
			if (s.contains("::~")) {
				String[] ss = s.split("::~");
				name = ss[0];
				// System.out.println(name);
				name1 = name.replaceAll("ApiHooker", "");
				// name0=name1.substring(0, name1.length()-1);
			}
			if (s.contains("*")) {
				String[] ss = s.split("\"");
				des = ss[1];
				// System.out.println(des);
			}
			if (s.contains("NULL")) {
				String[] ss = s.split("\"");
				name0 = ss[1];
				ss[3] = ss[3].replaceAll("L.+?;", "L").replace("(", "").replace(")", "").replace("[", "");
				StringBuffer sss = new StringBuffer(ss[3]);
				System.out.println(sss.toString());
				char cc=sss.charAt(sss.length()-1);
				sss.deleteCharAt(sss.length()-1);//.setCharAt(sss.length()-1, sss.charAt(0));
//				sss.setCharAt(0, cc);
//				shorty = sss.reverse().toString();
				shorty=cc+sss.toString();
				System.out.println(shorty);
			}
		}
		ff.saveToFile("hook", name + "* " + name1 + " = " + "new " + name + "();");
		ff.saveToFile("hook", "mApiHookerHashMap.insert(make_pair(\"" + name0 + "L" + des + ";" + shorty + "\","
				+ name1 + "));");
	}

	public static void main(String[] args) {
		geth("new", ".cpp");
	}
}

// class MyFilter implements FilenameFilter {
// private String type;
//
// public MyFilter(String type) {
// this.type = type;
// }
//
// public boolean accept(File dir, String name) {
// return name.endsWith(type);
// }
// }
