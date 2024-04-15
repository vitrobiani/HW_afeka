package com.testSys;

import java.io.Serializable;

public class Answer implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int AnswerIndex;
	protected boolean isCorrect;

	public enum eType {
		open, close
	};

	protected eType type;
	private AnswerRepository AR;

	// for the closed questions - need to set isCorrect
	public Answer(int AnsI, boolean isCorrect, AnswerRepository AR, eType type) {
		AnswerIndex = AnsI;
		this.isCorrect = isCorrect;
		this.AR = AR;
		this.type = type;
	}

	// for the open question - school answer is always true
	public Answer(int AnsI, AnswerRepository AR, eType type) {
		AnswerIndex = AnsI;
		this.AR = AR;
		this.type = type;
		this.isCorrect = true;
	}

	public int getAnswerIndex() {
		return AnswerIndex;
	}

	public boolean isCorrect() {
		return isCorrect;
	}

	public void setIsCorrect(boolean bool) {
		isCorrect = bool;
	}

	public eType getType() {
		return type;
	}

	public AnswerRepository getAR() {
		return AR;
	}

	public String getAnswer() {
		if (type == eType.close) {
			return AR.getClosedAns(AnswerIndex);
		} else {
			return AR.getOpenAns(AnswerIndex);
		}
	}

	public String toString() {
		StringBuffer sB = new StringBuffer();
		sB.append("the answer: " + (type == eType.open) != null ? AR.getOpenAns(AnswerIndex)
				: AR.getClosedAns(AnswerIndex) + '\n' + "it is: " + (isCorrect) != null ? "correct"
						: "incorrect" + '\n' + "its type is: " + type);

		return sB.toString();
	}

	public boolean equals(Answer a) {
		if (a.type == type && a.getAnswerIndex() == AnswerIndex && a.getType() == type) {
			return true;
		}
		return false;
	}
}
