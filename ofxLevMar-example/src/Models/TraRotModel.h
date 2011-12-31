#pragma once
//
//  TraRotModel.h
//  ofxLevMar-example
//


class TraRotModel : public Model<float> {
public:
	TraRotModel() : Model<float>(3, 3, 6) { }
	
	void evaluate(pfitDataPointf& point, const float *parameters) const {
		
		ofVec3f& x( *(ofVec3f*)point.getInput() );
		ofVec3f& y( *(ofVec3f*)point.getOutput() );
		
		const ofVec3f& R( *(const ofVec3f*)parameters );
		const ofVec3f& T( *(((const ofVec3f*)parameters)+1) );
		
		y = evaluate(x, R, T);
	}
	
	ofVec3f evaluate(const ofVec3f &x, const ofVec3f& R, const ofVec3f& T) const {
		return (x + T).rotate(R.x, R.y, R.z);
	}
};
