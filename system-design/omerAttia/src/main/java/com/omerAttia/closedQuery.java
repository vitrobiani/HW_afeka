package omerAttia;

import java.util.Arrays;
import java.util.Iterator;
import java.util.Random;

import omerAttia.Answer.eType;
import omerAttia.Query.difficulty;

public class closedQuery extends Query {
	private static final int maxAns = 5;
	private Answer[] AnswerList;

	public closedQuery(String q, difficulty diff, QueryRepository QR, Answer[] AnswerList) {
		super(q, diff, QR);
		this.AnswerList = AnswerList;
	}

	public closedQuery(String q, difficulty diff, QueryRepository QR) {
		super(q, diff, QR);
	}

	public boolean isAnswerInQuery(Answer cA) {
		for (int i = 0; i < AnswerList.length; i++) {
			if (AnswerList[i].equals(cA))
				return true;
		}
		return false;
	}

	public boolean addAnswerToQuery(int AnsI, boolean isCorrect, AnswerRepository AR) {
		Answer cA = new Answer(AnsI, isCorrect, AR, eType.close);
		if (!(isAnswerInQuery(cA)) && AnswerList.length <= maxAns) {
			Answer[] newAnswerList = Arrays.copyOf(AnswerList, AnswerList.length + 1);
			newAnswerList[newAnswerList.length - 1] = cA;
			AnswerList = newAnswerList;
			return true;
		}
		return false;
	}

	public void addAnswerToQuery(Answer cA) throws Exception {
		if ((isAnswerInQuery(cA)) || !(AnswerList.length <= maxAns)) {
			throw new Exception("to much answers or answer already exists");
		}
		Answer[] newAnswerList = Arrays.copyOf(AnswerList, AnswerList.length + 1);
		newAnswerList[newAnswerList.length - 1] = cA;
		AnswerList = newAnswerList;
	}

	public void rmAnAnswer(int aIndex) {
		Answer[] newAnswerList = new Answer[AnswerList.length - 1];
		for (int i = 0, k = 0; i < AnswerList.length; i++) {
			if (aIndex != i) {
				newAnswerList[k++] = AnswerList[i];
			}
		}
		AnswerList = newAnswerList;
	}

	public int getMaxAns() {
		return maxAns;
	}

	public Answer[] getAnswerList() {
		return AnswerList;
	}

	public String[] getStringAnswerList() {
		String[] StringAnswerList = new String[AnswerList.length];

		for (int i = 0; i < StringAnswerList.length; i++) {
			StringAnswerList[i] = AnswerList[i].getAnswer();
		}
		return StringAnswerList;
	}

	public void setAnswerList(Answer[] answerList) {
		AnswerList = answerList;
	}

	@Override
	public String toStringForTestRes() {
		StringBuffer sB = new StringBuffer(super.toString());
		int howManyCorrect = 0;
		for (int i = 0; i < AnswerList.length; i++) {
			if (AnswerList[i].isCorrect()) {
				howManyCorrect++;
			}
		}
		int i = 0;
		for (; i < AnswerList.length; i++) {
			sB.append("    " + (i + 1) + ")  " + AnswerList[i].getAnswer()
					+ ((AnswerList[i].isCorrect() && (howManyCorrect == 1)) ? "  |T|" : "  |F|") + '\n');
		}
		sB.append("    " + (++i) + ")  some of the answers are correct" + ((howManyCorrect > 1) ? "  |T|" : "  |F|")
				+ '\n');
		sB.append("    " + (++i) + ")  none of the answers are correct" + ((howManyCorrect == 0) ? "  |T|" : "  |F|")
				+ '\n');

		return sB.toString();
	}

	@Override
	public String toStringForTest() {
		Random r = new Random();
		int[] printRandom = new int[AnswerList.length];
		for (int i = 0; i < printRandom.length; i++) {
			boolean bool;
			int temp;
			do {
				bool = false;
				temp = r.nextInt(1, AnswerList.length + 1);
				for (int j = 0; j < printRandom.length; j++) {
					if (temp == printRandom[j]) {
						bool = true;
					}
				}
			} while (bool);
			printRandom[i] = temp;
		}

		StringBuffer sB = new StringBuffer(super.toString());
		int i = 0;
		for (; i < AnswerList.length; i++) {
			sB.append("    " + (i + 1) + ")  " + AnswerList[printRandom[i] - 1].getAnswer() + '\n');
		}
		sB.append("    " + (++i) + ")  some of the answers are correct" + '\n');
		sB.append("    " + (++i) + ")  none of the answers are correct" + '\n');

		return sB.toString();
	}

	public String toString() {
		StringBuffer sB = new StringBuffer(super.toString());
		for (int i = 0; i < AnswerList.length; i++) {
			sB.append("    " + (i + 1) + ")  " + AnswerList[i].getAnswer()
					+ ((AnswerList[i].isCorrect()) ? "  |T|" : "  |F|") + '\n');
		}
		return sB.toString();
	}

	public boolean equals(closedQuery q) {
		boolean b = true;
		for (int i = 0; i < AnswerList.length; i++) {
			if (!(q.getAnswerList()[i].equals(q.getAnswerList()[i]))) {
				b = false;
			}
		}
		return (super.equals(q) && b);
	}

}
