
package com.testSys;


public class openQuery extends Query {
	private Answer schoolAnswer;

	public openQuery(String q, difficulty diff, QueryRepository QR, Answer schoolAnswer) {
		super(q, diff, QR);
		this.schoolAnswer = schoolAnswer;
		schoolAnswer.setIsCorrect(true); // setting isCorrect in Answer to be true in schoolAnswer
	}

	public Answer getSchoolAnswer() {
		return schoolAnswer;
	}

	public String getCorrectAns() {
		return schoolAnswer.getAnswer();
	}

	public void setSchoolAnswer(Answer schoolAnswer) {
		this.schoolAnswer = schoolAnswer;
	}

	@Override
	public String toStringForTestRes() {
		StringBuffer sB = new StringBuffer(super.toString());
		sB.append("--->  " + getCorrectAns());
		return sB.toString();
	}

	@Override
	public String toStringForTest() {
		StringBuffer sB = new StringBuffer(super.toString() + '\n');
		sB.append("--->  ________________________________________________________\n"
				+ "      ________________________________________________________\n"
				+ "      ________________________________________________________\n");

		return sB.toString();
	}

	public String toString() {
		StringBuffer sB = new StringBuffer(super.toString());
		sB.append("--->  " + getCorrectAns());
		return sB.toString();
	}

	public boolean equals(openQuery q) {
		return super.equals(q) && (q.getSchoolAnswer().equals(schoolAnswer));
	}
}
