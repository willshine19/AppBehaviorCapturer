package testauto;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;

public class saveToFile {
	public void saveToFile(String name,String jo) {
		FileOutputStream fos = null	;
		PrintStream ps = null;
		try {
			String fileName = "/home/zds/file/"+name+".txt";
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
}
