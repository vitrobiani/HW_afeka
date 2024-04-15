package omerAttia;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.Serializable;
import java.util.Arrays;

import excersise.person;
import omerAttia.Query.difficulty;

public class QueryRepository implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Query[] allQueryArray;

	public QueryRepository(Query[] allQuerries) {
		this.allQueryArray = allQuerries;
	}

	public Query[] getAllQueryArray() {
		return allQueryArray;
	}

	public boolean isQueryInRep(Query q) {
		for (int i = 0; i < allQueryArray.length; i++) {
			if (allQueryArray[i].equals(q))
				return true;
		}
		return false;
	}

	public boolean addQuery(Query q) {
		if (!(isQueryInRep(q))) {
			Query[] newQList = Arrays.copyOf(allQueryArray, allQueryArray.length + 1);
			newQList[newQList.length - 1] = q;
			allQueryArray = newQList;
			return true;
		}
		return false;
	}

	public void rmQuery(int index) {
		Query[] newQueryArray = new Query[allQueryArray.length - 1];
		int k = 0;
		for (int i = 0; i < allQueryArray.length; i++) {
			if (i != index) {
				newQueryArray[k++] = allQueryArray[i];
			}
		}
		allQueryArray = newQueryArray;
	}

	public openQuery[] getOpenQueryArray() {
		int k = 0;
		for (int i = 0; i < allQueryArray.length; i++) {
			if (allQueryArray[i].getClass().equals(openQuery.class)) {
				k++;
			}
		}

		openQuery[] openQueryArray = new openQuery[k];
		for (int i = 0, t = 0; i < allQueryArray.length; i++) {
			if (allQueryArray[i].getClass().equals(openQuery.class)) {
				openQueryArray[t++] = (openQuery) allQueryArray[i];
			}
		}

		return openQueryArray;
	}

	public closedQuery[] getClosedQueryArray() {
		int k = 0;
		for (int i = 0; i < allQueryArray.length; i++) {
			if (allQueryArray[i].getClass().equals(closedQuery.class)) {
				k++;
			}
		}

		closedQuery[] closedQueryArray = new closedQuery[k];
		for (int i = 0, t = 0; i < allQueryArray.length; i++) {
			if (allQueryArray[i].getClass().equals(openQuery.class)) {
				closedQueryArray[t++] = (closedQuery) allQueryArray[i];
			}
		}
		return closedQueryArray;
	}

	public String closedQuerytoString() {
		StringBuffer sB = new StringBuffer();
		for (int i = 0; i < getClosedQueryArray().length; i++) {
			sB.append(getClosedQueryArray()[i].getOrdNum() + ")" + getClosedQueryArray()[i].toString() + '\n' + '\n');
		}
		return sB.toString();
	}

	public String openQuerytoString() {
		StringBuffer sB = new StringBuffer();
		for (int i = 0; i < getOpenQueryArray().length; i++) {
			sB.append(getOpenQueryArray()[i].getOrdNum() + ")" + getOpenQueryArray()[i].toString() + '\n' + '\n');
		}
		return sB.toString();
	}

	public void saveToFile() throws FileNotFoundException, IOException {
		ObjectOutputStream outFile = new ObjectOutputStream(new FileOutputStream("C:\\Users\\\\omer_\\\\Documents\\\\filesFromEclipse\\\\QueryRep.dat"));
		outFile.writeObject(allQueryArray);
		outFile.close();
	}
	
	public void readFromFile() throws FileNotFoundException, IOException, ClassNotFoundException {
		ObjectInputStream inFile = new ObjectInputStream(new FileInputStream("C:\\Users\\omer_\\Documents\\filesFromEclipse\\QueryRep.dat"));
		Query[] arr1 = (Query[]) inFile.readObject();
		inFile.close();
		allQueryArray = arr1;
	}
	
	public String toString() {
		StringBuffer sB = new StringBuffer();
		for (int i = 0; i < allQueryArray.length; i++) {
			sB.append((i + 1) + ".  " + allQueryArray[i].toString() + '\n' + '\n');
		}
		return sB.toString();
	}

	public boolean equals(QueryRepository Q) {
		return false;
	}
}
