/**
 * 读取.h文件，生成ApiHookerManager.h中的内容
 */
package testauto;

import java.io.File;
import java.io.FilenameFilter;
import java.util.Arrays;
import java.util.regex.Pattern;

public class readH {

	public static void geth(String name, final String arg) {
		File path = new File("/home/zds/file/" + name);
		MyFilter filter = new MyFilter(arg);
		String[] list = path.list(filter);
		Arrays.sort(list, String.CASE_INSENSITIVE_ORDER);
		for (String dirItem : list) {
			System.out.println(dirItem);
			new saveToFile().saveToFile("include", "#include \"../ApiHooker/Androidapi/" + dirItem + "\"");
		}
	}

	public static void main(String[] args) {
		geth("xuedi517", ".h");
	}
}

class MyFilter implements FilenameFilter {
	private String type;

	public MyFilter(String type) {
		this.type = type;
	}

	public boolean accept(File dir, String name) {
		return name.endsWith(type);
	}
}