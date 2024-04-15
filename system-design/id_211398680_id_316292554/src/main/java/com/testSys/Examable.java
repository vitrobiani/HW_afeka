
package com.testSys;


import java.io.FileNotFoundException;

public interface Examable {
	public void ManualExam() throws FileNotFoundException, Exception;
	public void AutomaticExam() throws Exception;
}
